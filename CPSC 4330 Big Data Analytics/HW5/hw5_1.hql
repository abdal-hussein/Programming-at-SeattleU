-- Justin Thoreson
-- 7 March 2022
-- hw5_1.hql

USE dualcore;

CREATE EXTERNAL TABLE IF NOT EXISTS loyalty_program (
	cust_id   INT,
	fname     STRING,
	lname     STRING,
	email     STRING,
	level     STRING,
	phones    MAP<STRING, STRING>,
	order_ids ARRAY<INT>,
	summary   STRUCT<minimum: INT,
		         maximum: INT,
		         average: FLOAT,
		         total:   INT>
)
ROW FORMAT DELIMITED
FIELDS TERMINATED BY '|'
COLLECTION ITEMS TERMINATED BY ','
MAP KEYS TERMINATED BY ':'
LOCATION '/user/hive/warehouse/dualcore.db/loyalty_program/data';
