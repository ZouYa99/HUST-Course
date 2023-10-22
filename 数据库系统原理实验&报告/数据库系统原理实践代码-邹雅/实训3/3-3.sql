-- 3) 查询既买了保险又买了基金的客户的名称、邮箱和电话。结果依c_id排序
-- 请用一条SQL语句实现该查询：

SELECT c_name, c_mail,c_phone
FROM client
WHERE c_id in (
    SELECT distinct c_id
    FROM client c1,property p1
    WHERE c1.c_id = p1.pro_c_id and p1.pro_type = 2
) and c_id in (
    SELECT distinct c_id
    FROM client c2,property p2
    WHERE c2.c_id = p2.pro_c_id and p2.pro_type = 3
)
order by c_id 

/*  end  of  your code  */