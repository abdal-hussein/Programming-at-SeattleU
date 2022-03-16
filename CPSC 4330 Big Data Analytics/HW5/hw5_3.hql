-- Justin Thoreson
-- 7 March 2022
-- hw5_3.hql

USE dualcore;

SELECT l.phones["HOME"]
FROM loyalty_program l
WHERE l.cust_id == 1200866; 