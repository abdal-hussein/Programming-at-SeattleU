-- Justin Thoreson
-- 7 March 2022
-- hw5_9.hql

USE dualcore;

SELECT EXPLODE(NGRAMS(SENTENCES(LOWER(r.message)), 3, 5)) AS trigrams
FROM ratings r
JOIN lowest_rating_info l
  ON r.prod_id == l.prod_id