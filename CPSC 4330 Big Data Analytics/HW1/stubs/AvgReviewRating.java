/**
 * CPSC 3300 Big Data Analytics
 * Homework 1
 * Generate the average rating for each product
 * 
 * @author Justin Thoreson
 * @version 1.0
 */

package stubs;

import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.conf.Configuration;

public class AvgReviewRating {

  public static void main(String[] args) throws Exception {

    // Validate that two arguments were passed from the command line.
    if (args.length != 2) {
      System.out.printf("Usage: AvgReviewRating <input dir> <output dir>\n");
      System.exit(-1);
    }

    /* 
     * Instantiate a Job object for your job's configuration.
     * Specify the jar file that contains your driver, mapper, and reducer.
     * Hadoop will transfer this jar file to nodes in your cluster running 
     * mapper and reducer tasks.
     */
    Configuration conf = new Configuration();
    Job job = Job.getInstance(conf, "avgreviewrating");
    job.setJarByClass(AvgReviewRating.class);
   
    // Set file input and output paths
    FileInputFormat.setInputPaths(job, new Path(args[0]));
    FileOutputFormat.setOutputPath(job, new Path(args[1]));
  
    // Set map and reducer classes.
    job.setMapperClass(ReviewMapper.class);
    job.setReducerClass(RatingReducer.class);
    
    // Set map output classes.
    job.setMapOutputKeyClass(Text.class);
    job.setMapOutputValueClass(IntWritable.class);
    
    // Set program output classes.
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(Text.class);
    
    // Start the MapReduce job and wait for it to finish.
    boolean success = job.waitForCompletion(true);
    System.exit(success ? 0 : 1);
  }
}

