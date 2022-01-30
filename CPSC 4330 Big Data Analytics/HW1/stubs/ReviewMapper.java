package stubs;
import java.io.IOException;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

public class ReviewMapper extends Mapper<LongWritable, Text, Text, IntWritable> {

  @Override
  public void map(LongWritable key, Text value, Context context)
      throws IOException, InterruptedException {

	// Define the indices of the productId and the starRating  
	final int PID_COL = 3;
	final int STAR_COL = 7;
	
	// Split each line of the input with tab delimiter
    String[] words = value.toString().split("\\t+");
    
    // Extract the productId
    String productId = words[PID_COL];
    
    try {
    	
    	// Extract the starRating
	    int starRating = Integer.parseInt(words[STAR_COL]);
	    
	    // Send out intermediate data
	    if (productId.length() > 0) {
	    	context.write(new Text(productId), new IntWritable(starRating));
	    }
	    
    } catch (NumberFormatException e) {
    	e.printStackTrace();
    	System.out.println("Failed to extract a rating");
    	System.out.println("The value encountered is likely a header label");
    }

  }
}
