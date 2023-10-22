use finance1;
drop trigger if exists before_property_inserted;
-- 请在适当的地方补充代码，完成任务要求：
delimiter $$
CREATE TRIGGER before_property_inserted BEFORE INSERT ON property
FOR EACH ROW 
BEGIN
declare msg varchar(128);
if new.pro_type not in (1,2,3) then
    set msg = concat('type ', cast(new.pro_type as char), ' is illegal!');
    signal sqlstate '45000' set message_text = msg;
end if;
if (new.pro_type = 1 and new.pro_pif_id not in(select distinct p_id from finances_product)) then
    set msg = concat('finances product #', cast(new.pro_pif_id as char), ' not found!');
    signal sqlstate '45000' set message_text = msg;
end if;
if (new.pro_type = 2 and new.pro_pif_id not in(select distinct i_id from insurance)) then
    set msg = concat('insurance #', cast(new.pro_pif_id as char), ' not found!');
    signal sqlstate '45000' set message_text = msg;
    end if;
if (new.pro_type = 3 and new.pro_pif_id not in(select distinct f_id from fund)) then
    set msg = concat('fund #', cast(new.pro_pif_id as char), ' not found!');
    signal sqlstate '45000' set message_text = msg;
end if;


END$$
 
delimiter ;











