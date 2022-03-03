"""Justin Thoreson
02/15/2022
hw3_2.py

This script processes various works of Shakespeare. The script will extract and
output the top ten most popular words used within provided Shakespeare files.
"""

from pyspark import SparkContext
import sys
import re

def topTenWords(sc : SparkContext) -> None:
    """Finds the top ten most popular words in the Shakespeare files
    
    :param sc: SparkContext object
    """
    
    # Get Shakespeare and stopword files
    shakespeare = sc.textFile(sys.argv[1])
    stopwords = sc.textFile('file:/hadoop-data/stopwords.txt').collect()

    # Remove punctuation, unnecessary whitespace, empty lines, flatmap
    shakeRemPunc = shakespeare.map(lambda line : re.sub(r'[^A-Za-z0-9\s\']', '', line)) \
        .flatMap(lambda line : line.lower().split()) \
        .filter(lambda line : len(line) > 0)

    # Remove stop words
    shakeRemStop = shakeRemPunc.filter(lambda word : word not in stopwords) \
        .map(lambda word : re.sub('\'', '', word))

    # Reduce by key, sort by value
    shakeReduce = shakeRemStop.map(lambda word : (word, 1)) \
        .reduceByKey(lambda v1, v2 : v1 + v2) \
        .sortBy(lambda word : word[1], ascending=False)

    # Extract top ten words and save output
    shakeTopTen = sc.parallelize(shakeReduce.take(10))
    shakeTopTen.saveAsTextFile(sys.argv[2])

def main() -> None:
    """Runs the Spark job to find the top ten words in Shakespeare's works"""

    if len(sys.argv) != 3:
        print("Usage: hw3_2.py <input> <output>", file=sys.stderr)
        exit(-1)

    # Init SparkContext and run job
    sc = SparkContext()
    topTenWords(sc)
    sc.stop()

if __name__ == "__main__":
    main()