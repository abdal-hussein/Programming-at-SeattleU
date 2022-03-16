-- Justin Thoreson
-- 7 March 2022
-- hw5_2.hql

USE dualcore;

LOAD DATA INPATH '/user/hive/warehouse/dualcore.db/loyalty_program/loyalty_data.txt'
INTO TABLE loyalty_program;