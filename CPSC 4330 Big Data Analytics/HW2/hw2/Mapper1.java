package hw2;

import java.io.IOException;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

public class Mapper1 extends Mapper<LongWritable, Text, Text, Text>{
	
	@Override
	public void map(LongWritable key, Text value, Context context) 
			throws IOException, InterruptedException {
		
		// Define the indices of the productId, customerId, and starRating
		final int CUST_COL = 1;
		final int PID_COL = 3;
		final int STAR_COL = 7;
		
		// Split each line of the input with tab delimiter
	    String[] reviewSplit = value.toString().split("\\t+");
	    
	    if (reviewSplit.length > 7) {
	    	
	    	// End program if first line is header
	    	if (reviewSplit[0].equals("marketplace")) return;
		    
	    	// Extract the customerId and the productId
		    String customerId = reviewSplit[CUST_COL];
		    String productId = reviewSplit[PID_COL];
		    String ratingTxt = reviewSplit[STAR_COL];
		    
		    if (customerId.length() > 0 && productId.length() > 0 && 
		    		ratingTxt.length() > 0) {
		    	
			    try {
			    	// Extract the starRating
			    	int starRating = Integer.parseInt(ratingTxt);
			    	
			    	// Map productId as key with customerId as value
				    if (starRating >= 4) {
				    	context.write(new Text(productId), new Text(customerId));
				    }
			    } catch (NumberFormatException e) {
			    	System.out.printf("ERROR: Failed to extract rating." +
			    			"Could not parse integer value.");
			    	e.printStackTrace();
			    }
		    }
	    }
	}
}