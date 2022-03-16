-- Justin Thoreson
-- 7 March 2022
-- hw5_5.hql

USE dualcore;

SELECT COUNT(d.prod_id) AS num_products
FROM orders o
JOIN order_details d
  ON o.order_id == d.order_id
WHERE o.cust_id == 1071189;