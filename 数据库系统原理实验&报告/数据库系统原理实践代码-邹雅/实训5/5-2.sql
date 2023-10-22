 -- 基于上一关创建的视图v_insurance_detail进行分组统计查询，列出每位客户的姓名，身份证号，保险投资总额(insurance_total_amount)和保险投资总收益(insurance_total_revenue),结果依保险投资总额降序排列。
--  请用一条SQL语句实现该查询：

select distinct c_name,c_id_card,ifnull(
    (select sum(pro_quantity*i_amount) from v_insurance_detail v2
    where v1.c_name = v2.c_name),0
) as insurance_total_amount,ifnull(
    (select sum(pro_income) from v_insurance_detail v3
    where v1.c_name = v3.c_name),0
) as insurance_total_revenue 
from v_insurance_detail v1
order by insurance_total_amount desc;


/*  end  of  your code  */