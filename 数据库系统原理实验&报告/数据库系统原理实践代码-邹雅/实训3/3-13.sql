-- 13) 综合客户表(client)、资产表(property)、理财产品表(finances_product)、
--     保险表(insurance)、基金表(fund)和投资资产表(property)，
--     列出所有客户的编号、名称和总资产，总资产命名为total_property。
--     总资产为储蓄卡余额，投资总额，投资总收益的和，再扣除信用卡透支的金额
--     (信用卡余额即为透支金额)。客户总资产包括被冻结的资产。
--    请用一条SQL语句实现该查询：


select c_id,c_name,ifnull(
    (select sum(b_balance)
    from bank_card
    where c_id = b_c_id and b_type = '储蓄卡'),0
) + 
ifnull(
    (select sum(pro_income)
    from property
    where c_id = pro_c_id),0
) +
ifnull(
    (select sum(pro_quantity*p_amount)
    from property,finances_product 
    where c_id = pro_c_id and pro_type = 1 and p_id = pro_pif_id),0
) +
ifnull(
    (select sum(pro_quantity*i_amount)
    from property,insurance
    where c_id = pro_c_id and pro_type = 2 and i_id = pro_pif_id),0
) + 
ifnull(
    (select sum(pro_quantity*f_amount)
    from property,fund
    where c_id = pro_c_id and pro_type = 3 and f_id = pro_pif_id),0
) - 
ifnull(
    (select sum(b_balance)
    from bank_card
    where c_id = b_c_id and b_type = '信用卡'),0
)
as total_property
from client;




/*  end  of  your code  */ 