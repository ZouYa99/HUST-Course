-- 17 查询2022年2月购买基金的高峰期。至少连续三个交易日，所有投资者购买基金的总金额超过100万(含)，则称这段连续交易日为投资者购买基金的高峰期。只有交易日才能购买基金,但不能保证每个交易日都有投资者购买基金。2022年春节假期之后的第1个交易日为2月7日,周六和周日是非交易日，其余均为交易日。请列出高峰时段的日期和当日基金的总购买金额，按日期顺序排序。总购买金额命名为total_amount。
--    请用一条SQL语句实现该查询：

WITH t1 AS(
SELECT *
FROM (
    SELECT pro_purchase_time, SUM(pro_quantity * f_amount) AS total_amount, ROW_NUMBER() OVER(ORDER BY pro_purchase_time) AS _date
    FROM property JOIN fund ON pro_pif_id = f_id
    WHERE pro_purchase_time >= '2022-02-01'
    GROUP BY pro_purchase_time
) AS _t1
WHERE total_amount >= 1000000
), 
t2 AS(
SELECT *
FROM (
    SELECT pro_purchase_time, SUM(pro_quantity * f_amount) AS total_amount, ROW_NUMBER() OVER(ORDER BY pro_purchase_time) AS _date
    FROM property JOIN fund ON pro_pif_id = f_id
    WHERE pro_purchase_time >= '2022-02-01'
    GROUP BY pro_purchase_time
) AS _t2
WHERE total_amount >= 1000000
), 
t3 AS(
SELECT *
FROM (
    SELECT pro_purchase_time, SUM(pro_quantity * f_amount) AS total_amount, ROW_NUMBER() OVER(ORDER BY pro_purchase_time) AS _date
    FROM property JOIN fund ON pro_pif_id = f_id
    WHERE pro_purchase_time >= '2022-02-01'
    GROUP BY pro_purchase_time
) AS _t3
WHERE total_amount >= 1000000
)
SELECT *
FROM (
    (SELECT t1.pro_purchase_time AS pro_purchase_time, t1.total_amount AS total_amount
     FROM (t1 JOIN t2 ON t1._date + 1 = t2._date) JOIN t3 ON t2._date + 1 = t3._date 
         AND t1.pro_purchase_time + 2 <> t2.pro_purchase_time AND t2.pro_purchase_time + 2 <> t3.pro_purchase_time)
     UNION
     (SELECT t2.pro_purchase_time AS pro_purchase_time, t2.total_amount AS total_amount
     FROM (t1 JOIN t2 ON t1._date + 1 = t2._date) JOIN t3 ON t2._date + 1 = t3._date
         AND t1.pro_purchase_time + 2 <> t2.pro_purchase_time AND t2.pro_purchase_time + 2 <> t3.pro_purchase_time)
     UNION
     (SELECT t3.pro_purchase_time AS pro_purchase_time, t3.total_amount AS total_amount
     FROM (t1 JOIN t2 ON t1._date + 1 = t2._date) JOIN t3 ON t2._date + 1 = t3._date
         AND t1.pro_purchase_time + 2 <> t2.pro_purchase_time AND t2.pro_purchase_time + 2 <> t3.pro_purchase_time)
) AS t
ORDER BY pro_purchase_time;

/*  end  of  your code  */