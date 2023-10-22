use fib;

-- 创建存储过程`sp_fibonacci(in m int)`，向表fibonacci插入斐波拉契数列的前m项，及其对应的斐波拉契数。fibonacci表初始值为一张空表。请保证你的存储过程可以多次运行而不出错。

drop procedure if exists sp_fibonacci;
delimiter $$
create procedure sp_fibonacci(in m int)
begin
######## 请补充代码完成存储过程体 ########
if m = 1 then
insert into fibonacci values(0,0);
elseif m = 2 then
insert into fibonacci values(0,0);
insert into fibonacci values(1,1);
else
    insert into fibonacci values(0,0);
    insert into fibonacci values(1,1);
    set @n = m - 2;
    set @i = 3;
    while @n > 0 do
        set @F1 = (select fibn from fibonacci where n = @i-2);
        set @F2 = (select fibn from fibonacci where n = @i-3);
        set @FF = @F1+@F2;
        insert into fibonacci values(@i-1,@FF);
        set @n = @n - 1;
        set @i = @i + 1;
    end while;
end if;

end $$

delimiter ;

 
