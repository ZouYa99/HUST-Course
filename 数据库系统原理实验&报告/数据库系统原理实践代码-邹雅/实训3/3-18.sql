 -- 18) 查询至少有一张信用卡余额超过5000元的客户编号，以及该客户持有的信用卡总余额，总余额命名为credit_card_amount。
--    请用一条SQL语句实现该查询：

select b_c_id,(
    select sum(b_balance)
    from bank_card b2
    where b1.b_c_id = b2.b_c_id and b_type = '信用卡'
)credit_card_amount
from bank_card b1
where b_type = '信用卡'
group by b_c_id
having sum(if(b_balance > 5000,1,0)) >= 1
order by b_c_id;


/*  end  of  your code  */


 