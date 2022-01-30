package stubs;
import java.io.IOException;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

public class RatingReducer extends Reducer<Text, IntWritable, Text, Text> {

  @Override
  public void reduce(Text key, Iterable<IntWritable> values, Context context)
      throws IOException, InterruptedException {
	  
	  // Track numReviews and sumRatings for each product
	  int numReviews = 0;
	  int sumRatings = 0;
	  
	  for (IntWritable value : values) {
		  sumRatings += value.get();
		  numReviews++;
	  }
	  
	  // Calculate avgRating
	  double avgRating = (double)sumRatings/numReviews;
	  
	  // Write reducer output
	  context.write(key, new Text(Integer.toString(numReviews) 
			  + "\t" + Double.toString(avgRating)));
  }
}