select
    employee_name
from
    employee natural left outer join manages
where
    manager_name is null

select
    employee_name
from
    employee as e
where
    not exists(
        select
            employee_name
        from
            manages as m
        where
            e.employee_name = m.employee_name
            and m.manager_name is not null
    )