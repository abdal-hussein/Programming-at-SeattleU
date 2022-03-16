-- Justin Thoreson
-- 7 March 2022
-- hw5_4.hql

USE dualcore;

SELECT l.order_ids[2]
FROM loyalty_program l
WHERE l.cust_id == 1200866;