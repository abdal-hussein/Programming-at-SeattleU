"""Justin Thoreson
02/15/2022
hw3_1.py

This script processes reviews for Amazon products. The script will compute the
average review rating for each product in a supplied Amazon review file.
"""

from pyspark import SparkContext
import sys

def avgReviewRating(sc : SparkContext) -> None:
    """Computers the average ratings for Amazon products

    :param sc: SparkContext object 
    """

    # Get review file
    reviews = sc.textFile(sys.argv[1])

    # Extract product id and star rating
    productRatings = reviews.map(lambda review : review.split("\t")) \
        .filter(lambda review : review[0] != "marketplace" and len(review) > 7) \
        .map(lambda review : (review[3], (int(review[7]), 1)))
    
    # Get sum of ratings and number of ratings
    sumRatings = productRatings.reduceByKey(lambda v1, v2: (v1[0] + v2[0], v1[1] + v2[1])) \
        .sortByKey()
    
    # Compute average rating and save output
    avgReviewRating = sumRatings.map(lambda review : (review[0], review[1][0]/review[1][1], review[1][1]))
    avgReviewRating.saveAsTextFile(sys.argv[2])

def main() -> None:
    """Runs the Spark job to compute average review ratings"""

    if len(sys.argv) != 3:
        print("\nUsage: hw3_1.py <input> <output>", file=sys.stderr)
        exit(-1)
    
    # Init SparkContext and run job
    sc = SparkContext()
    avgReviewRating(sc)
    sc.stop()

if __name__ == "__main__":
    main()