-- 15) 查询资产表中客户编号，客户基金投资总收益,基金投资总收益的排名(从高到低排名)。
--     总收益相同时名次亦相同(即并列名次)。总收益命名为total_revenue, 名次命名为rank。
--     第一条SQL语句实现全局名次不连续的排名，
--     第二条SQL语句实现全局名次连续的排名。

-- (1) 基金总收益排名(名次不连续)
select distinct pro_c_id, total_revenue,(
    select count(income_sum) + 1
    from (
        select distinct pro_c_id,sum(pro_income) income_sum
        from property p3
        where pro_type = 3
        group by pro_c_id
    ) as income_m
    where income_sum > total_revenue
) as `rank`
from (select pro_c_id,sum(pro_income) total_revenue
        from property
        where pro_type = 3
        group by pro_c_id
) as income_m
order by total_revenue desc,pro_c_id;
-- (2) 基金总收益排名(名次连续)
select distinct pro_c_id, total_revenue,(
    select count(distinct income_sum)
    from (
        select distinct pro_c_id,sum(pro_income) income_sum
        from property p3
        where pro_type = 3
        group by pro_c_id
    ) as income_m
    where income_sum >= total_revenue
) as `rank`
from (select pro_c_id,sum(pro_income) total_revenue
        from property
        where pro_type = 3
        group by pro_c_id
) as income_m
order by total_revenue desc,pro_c_id;


/*  end  of  your code  */