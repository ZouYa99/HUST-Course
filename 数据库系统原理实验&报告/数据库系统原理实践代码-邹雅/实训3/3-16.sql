-- 16) 查询持有相同基金组合的客户对，如编号为A的客户持有的基金，编号为B的客户也持有，反过来，编号为B的客户持有的基金，编号为A的客户也持有，则(A,B)即为持有相同基金组合的二元组，请列出这样的客户对。为避免过多的重复，如果(1,2)为满足条件的元组，则不必显示(2,1)，即只显示编号小者在前的那一对，这一组客户编号分别命名为c_id1,c_id2。

-- 请用一条SQL语句实现该查询：

select distinct p1.pro_c_id c_id1,p2.pro_c_id c_id2
from property p1,property p2
where p1.pro_type = 3 and p1.pro_c_id < p2.pro_c_id 
and not exists(
    select * from property p3 
    where p3.pro_c_id = p1.pro_c_id and p3.pro_type = 3 and not exists(
        select * from property p4
        where p4.pro_c_id = p2.pro_c_id and p4.pro_type = 3 
        and p3.pro_pif_id = p4.pro_pif_id
    )
)
and not exists(
    select * from property p3 
    where p3.pro_c_id = p2.pro_c_id and p3.pro_type = 3 and not exists(
        select * from property p4
        where p4.pro_c_id = p1.pro_c_id and p4.pro_type = 3 
        and p3.pro_pif_id = p4.pro_pif_id
    )
)
order by p1.pro_c_id;



/*  end  of  your code  */