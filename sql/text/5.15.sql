a.
create function avg salary(company_name varchar(15)) 
    returns integer 
    declare result integer;-- 返回值为int
        select
            avg(salary) into result --将平均工资返回到result中
        from
            works
        where
            works.company_name = company_name 
        return result;
end

select
    company_name
from
    works
where
    avg salary(company_name) > avg salary("First Bank Corporation")

b.
select
    company_name
from
    works
group by
    company_name
having
    avg(salary) > (
        select
            avg(salary)
        from
            works
        where
            company_name = "First Bank Corporation"
    )