package hw2;

import java.io.IOException;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.mapreduce.Mapper;

public class Mapper2 extends Mapper<LongWritable, Text, UserPairWritable, Text>{
		
	@Override
	public void map(LongWritable key, Text value, Context context) 
			throws IOException, InterruptedException {
		
		// Split the input line
		String[] lineSplit = value.toString().split("\\s+");
		
		if (lineSplit.length > 2) {
			
			// Extract user pair and productId from line
			String user1 = lineSplit[0];
			String user2 = lineSplit[1];
			String productId = lineSplit[2];
			
			if (user1.length() > 0 && user2.length() > 0 &&
					productId.length() > 0) {
				
				// Map user pair as key and productId to value
				UserPairWritable pair = new UserPairWritable(user1, user2);
				context.write(pair, new Text(productId));
			}
		}
	}
}