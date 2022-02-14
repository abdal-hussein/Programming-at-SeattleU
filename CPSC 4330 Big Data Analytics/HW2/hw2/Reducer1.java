package hw2;

import java.util.ArrayList;
import java.io.IOException;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

public class Reducer1 extends Reducer<Text, Text, UserPairWritable, Text>{
	
	@Override
	public void reduce(Text key, Iterable<Text> values, Context context)
			throws IOException, InterruptedException {
		
		// Create copy of iterable to prevent accidental iteration
		// Remove duplicate instances of customers
		ArrayList<String> customers = new ArrayList<String>();
		for (Text value : values) {
			if (!customers.contains(value.toString())) {
				customers.add(value.toString());
			}
		}
		
		// Create pairs of users
		for (int i = 0; i < customers.size() - 1; i++) {
			for (int j = i + 1; j < customers.size(); j++) {
				
				// Take two cusomers
				String left = customers.get(i);
				String right = customers.get(j);
				
				// Order the pair of customers
				int order = left.compareTo(right);
				String user1 = order < 0 ? left.toString() : right.toString();
				String user2 = order < 0 ? right.toString() : left.toString();
				UserPairWritable pair = new UserPairWritable(user1, user2);
				
				// Output user pair as key with productId as value
				context.write(pair, key);
			}
		}
	}
}