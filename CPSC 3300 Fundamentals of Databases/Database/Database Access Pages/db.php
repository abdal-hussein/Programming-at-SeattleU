<!-- db.php
     A PHP script to access the sailor database
     through MySQL
     -->
<html>
<head>
<title> Access the cars database with MySQL </title>
</head>
<body>
<?php

// Connect to MySQL

$servername = "cssql.seattleu.edu";
$username = "user24";
$password = "1234";

print $servername;

$conn = mysql_connect($servername, $username, $password);

if (!$conn) {
     print "Error - Could not connect to MySQL";
     exit;
}

// Select the movie database named test
$db = mysql_select_db("bw_db24", $conn);
if (!$db) {
    print "Error - Could not select the event database";
    exit;
}

// For select
$attr = $_POST['attr'] ? "SELECT " . $_POST['attr'] : "SELECT *";
$table = $_POST['table'];
$condition = $_POST['condition'] ? " WHERE " . $_POST['condition'] : "";
$groupby = $_POST['groupby'] ? " GROUP BY " . $_POST['groupby'] : "";
$having = $_POST['having'] ? " HAVING " . $_POST['having'] : "";
$limit = $_POST['limit'] ? " LIMIT " . $_POST['limit'] : "";

// For insert
$insert = $_POST['insert'];
$into = $_POST['into'];

// For describe
$desc = $_POST['desc'];

// For delete
$delTable = $_POST['delTable'];
$delCondition = $_POST['delCondition'];

if ($table)
    $query = $attr . " FROM " . $table . $condition . $groupby . $having . $limit;
else if ($insert && $into)
    $query = "INSERT INTO " . $into . " VALUES (" . $insert . ")";
else if ($desc)
    $query = "DESC " . $desc;
else if ($delTable && $delCondition)
    $query = "DELETE FROM " . $delTable . " WHERE " . $delCondition;

// Clean up the given query (delete leading and trailing whitespace)
trim($query);

// remove the extra slashes
$query = stripslashes($query);

// Home page button redirect
print "<p> Back to home page:
           <a href = \"http://css1.seattleu.edu/~thoresonjust/db3300/db_home.html\">
                Justin's Database
           <a>
      </p>";

// handle HTML special characters
$query_html = htmlspecialchars($query);
print "<p> <b> The query is: </b> " . $query_html . "</p>";

// Execute the query
$result = mysql_query($query);
if (!$result) {
    print "Error - the query could not be executed";
    $error = mysql_error();
    print "<p>" . $error . "</p>";
    exit;
}

// Get the number of rows in the result
$num_rows = mysql_num_rows($result);
print "Number of rows = $num_rows <br />";

// Get the number of fields in the rows
$num_fields = mysql_num_fields($result);
print "Number of fields = $num_fields <br />";

// Get the first row
$row = mysql_fetch_array($result);

// Display the results in a table
if ($desc)
    print "<table border='border'><caption> <h2> " . $desc . " </h2> </caption>";
else
    print "<table border='border'><caption> <h2> Query Results </h2> </caption>";
print "<tr align = 'center'>";

// Produce the column labels
$keys = array_keys($row);
for ($index = 0; $index < $num_fields; $index++) 
    print "<th>" . $keys[2 * $index + 1] . "</th>";

print "</tr>";

// Output the values of the fields in the rows
for ($row_num = 0; $row_num < $num_rows; $row_num++) {

    print "<tr align = 'center'>";
    $values = array_values($row);
	
    for ($index = 0; $index < $num_fields; $index++){
        $value = htmlspecialchars($values[2 * $index + 1]);
        print "<td>" . $value . "</td> ";
    }

    print "</tr>";
    $row = mysql_fetch_array($result);
}

print "</table>";

// Home page button redirect
print "<p> Back to home page:
           <a href = \"http://css1.seattleu.edu/~thoresonjust/db3300/db_home.html\">
                Justin's Database
           <a>
      </p>";

mysql_close($conn);
?>
</body>
</html>
