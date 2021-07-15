### 3.8 #### a. (
SELECT
	​ customer_name
FROM
	​ depositor
)
except
	(
		​
		SELECT
			​ customer_name ​
		FROM
			​ borrower
	) #### b.
SELECT
	F.customer_name
FROM
	customer
	JOIN customer S USING (customer street, customer city)
WHERE
	S.customer name = 'Smith' #### c. 
SELECT
	Distinct branch name
FROM
	account Natural
	JOIN depositor Natural
	JOIN customer
WHERE
	customer city = 'Harrison' ### 3.9 #### a. 
SELECT
	e.employee_name,
	city
FROM
	employee e,
	works w
WHERE
	w.company_name = 'First Bank Corporation'
	AND w.employee_name = e.employee_name #### b. 
SELECT
	*
FROM
	employee
WHERE
	employee_name IN (
		SELECT
			employee_name
		FROM
			works
		WHERE
			company_name = 'First Bank Corporation'
			AND salary > 10000
	) #### c. 
SELECT
	employee_name
FROM
	employee
WHERE
	employee_name not IN (
		SELECT
			employee_name
		FROM
			works
		WHERE
			company_name = 'First Bank Corporation'
	) #### d. 
SELECT
	employee_name
FROM
	works
WHERE
	salary > all (
		SELECT
			salary
		FROM
			works
		WHERE
			company_name = 'Small Bank Corporation'
	) #### e. 
SELECT
	S.company_name
FROM
	company S
WHERE
	not exists (
		(
			SELECT
				city
			FROM
				company
			WHERE
				company_name = 'Small Bank Corporation'
		)
		except
			(
				SELECT
					city
				FROM
					company T
				WHERE
					S.company_name = T.company_name
			)
	) #### f. 
SELECT
	company_name
FROM
	works
GROUP BY
	company_name
HAVING
	count (distinct employee_name) >= all (
		SELECT
			count (distinct employee_name)
		FROM
			works
		GROUP BY
			company_name
	) #### g.
SELECT
	company_name
FROM
	works
GROUP BY
	company_name
HAVING
	avg (salary) > (
		SELECT
			avg (salary)
		FROM
			works
		WHERE
			company_name = 'First Bank Corporation'
	) ### 3.10 ####a. update employee 
SET
	city = 'Newton'
WHERE
	person name = 'Jones' ####b. update works T 
SET
	T.salary = T.salary ∗ (
		CASE
			WHEN (T.salary ∗ 1.1 > 100000) THEN 1.03
			else 1.1
		)
		WHERE
			T.employee name IN (
				SELECT
					manager name
				FROM
					manages
			)
			AND T.company name = 'First Bank Corporation' ### 3.15 #### a. with branchcount AS ( 
		SELECT
			COUNT(*) branch
		WHERE
			branch_city = 'Brooklyn'
	)
SELECT
	customer_name
FROM
	customer AS A
WHERE
	branchcount = (
		SELECT
			COUNT(distinct branch_name)
		FROM
			(
				customer natural
				JOIN depositor natural
				JOIN account natural
				JOIN branch
			) AS B
		WHERE
			B.customer_name = A.customer_name
	) ####b. 
SELECT
	SUM(amount)
FROM
	loan ####c.
SELECT
	branch_name
FROM
	branch
WHERE
	assets > some (
		SELECT
			assets
		FROM
			branch
		WHERE
			branch_city = 'Brooklyn'
	)