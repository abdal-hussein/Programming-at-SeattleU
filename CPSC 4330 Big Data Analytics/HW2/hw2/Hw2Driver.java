/**
 * CPSC 3300 Big Data Analytics
 * Homework 2
 * Generate pairs of customers who provided a rating of four or above
 * to three common products. Utilization of chained jobs.
 * 
 * @author Justin Thoreson
 * @version 1.0
 */

package hw2;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class Hw2Driver {
	
	public static void main (String[] args) throws Exception {
		
		/*** Setup ***/
		
		if (args.length != 3) {
			System.out.printf("Usage: Hw2Driver <input dir>" + 
					"<temp output dir> <final output dir>\n");
			System.exit(-1);
		}
		
		Configuration config = new Configuration();
		
		/*** Job 1 ***/
		
		// Configure job 1
		Job job1 = Job.getInstance(config, "job1");
		job1.setJarByClass(Hw2Driver.class);
		
		// Set job 1 input and output directories
		FileInputFormat.setInputPaths(job1, new Path(args[0]));
		FileOutputFormat.setOutputPath(job1, new Path(args[1]));
		
		// Set job 1 mapper and reducer
		job1.setMapperClass(Mapper1.class);
		job1.setReducerClass(Reducer1.class);
		
		// Set job 1 mapper output classes
		job1.setMapOutputKeyClass(Text.class);
		job1.setMapOutputValueClass(Text.class);
		
		// Set job 1 reducer output classes
		job1.setOutputKeyClass(UserPairWritable.class);
		job1.setOutputValueClass(Text.class);
		
		// Wait for job 1 completion
		boolean success = job1.waitForCompletion(true);
		if (!success) {
			System.out.printf("Job 1 failed, exiting\n");
			System.exit(1);
		}
		
		/*** Job 2 ***/
		
		// Configure job 2
		Job job2 = Job.getInstance(config, "job2");
		job2.setJarByClass(Hw2Driver.class);
		
		// Set job2 input and output directories
		FileInputFormat.setInputPaths(job2, new Path(args[1]));
		FileOutputFormat.setOutputPath(job2, new Path(args[2]));
		
		// Set job 2 mapper and reducer
		job2.setMapperClass(Mapper2.class);
		job2.setReducerClass(Reducer2.class);
		
		// Set job 2 mapper output classes
		job2.setMapOutputKeyClass(UserPairWritable.class);
		job2.setMapOutputValueClass(Text.class);
		
		// Set job 2 reducer output classes
		job2.setOutputKeyClass(UserPairWritable.class);
		job2.setOutputValueClass(Text.class);
		
		// Wait for job 2 completion
		success = job2.waitForCompletion(true);
		System.exit(success ? 0 : 1);
	}
}