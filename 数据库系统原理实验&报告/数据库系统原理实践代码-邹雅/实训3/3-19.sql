-- 19) 以日历表格式列出2022年2月每周每日基金购买总金额，输出格式如下：
-- week_of_trading Monday Tuesday Wednesday Thursday Friday
--               1
--               2    
--               3
--               4
--   请用一条SQL语句实现该查询：
select distinct week(pro_purchase_time) - 5 as week_of_trading,(
    select sum(pro_quantity*f_amount)
    from property p2,fund
    where week_of_trading+5 = week(p2.pro_purchase_time) 
    and weekday(p2.pro_purchase_time) = 0 and p2.pro_pif_id = f_id 
    and p2.pro_type = 3 and year(p2.pro_purchase_time) = 2022
) as Monday,(
    select sum(pro_quantity*f_amount)
    from property p2,fund
    where week_of_trading+5 = week(p2.pro_purchase_time) 
    and weekday(p2.pro_purchase_time) = 1 and p2.pro_pif_id = f_id 
    and p2.pro_type = 3 and year(p2.pro_purchase_time) = 2022
) as Tuesday,(
    select sum(pro_quantity*f_amount)
    from property p2,fund
    where week_of_trading+5 = week(p2.pro_purchase_time) 
    and weekday(p2.pro_purchase_time) = 2 and p2.pro_pif_id = f_id 
    and p2.pro_type = 3 and year(p2.pro_purchase_time) = 2022
) as Wednesday,(
    select sum(pro_quantity*f_amount)
    from property p2,fund
    where week_of_trading+5 = week(p2.pro_purchase_time) 
    and weekday(p2.pro_purchase_time) = 3 and p2.pro_pif_id = f_id 
    and p2.pro_type = 3 and year(p2.pro_purchase_time) = 2022
) as Thursday,(
    select sum(pro_quantity*f_amount)
    from property p2,fund
    where week_of_trading+5 = week(p2.pro_purchase_time) 
    and weekday(p2.pro_purchase_time) = 4 and p2.pro_pif_id = f_id 
    and p2.pro_type = 3 and year(p2.pro_purchase_time) = 2022
) as Friday
from property p1
where year(pro_purchase_time) = 2022 and month(pro_purchase_time) = 2;





/*  end  of  your code  */