package hw2;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

public class Reducer2 extends Reducer<UserPairWritable, Text, UserPairWritable, Text>{
	
	@Override
	public void reduce(UserPairWritable key, Iterable<Text> values, Context context)
			throws IOException, InterruptedException {
	 
		// Create copy of iterable to prevent accidental iteration 
		ArrayList<String> productIds = new ArrayList<String>();
		for (Text value : values) {
			productIds.add(value.toString());
		}
		
		// Sort productIds in descending order for readability
		Collections.sort(productIds);
		Collections.reverse(productIds);
		
		// Set output if number of common products is at least 3
		if (productIds.size() >= 3) {
			
			// Format product output
			String products = productIds.get(0);
			for (int i = 1; i < productIds.size(); i++) {
				products += "," + productIds.get(i);
			}
			
			// Output user pair as key and products as value
			context.write(key, new Text(products));
		}
	}
}