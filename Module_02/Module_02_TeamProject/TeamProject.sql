select * from product;
select * from account;
select * from product_type;
select * from product_category;
select * from branch;
select * from customer;


-- 1. 고객의 평균나이를 검색하라. (나이는 소숫점은 제외하고 정수로 반올림하라) (10점)
SELECT ROUND(AVG(age)) as 고객평균나이
FROM customer;


-- 2. 계좌를 많이 개설한 지점순으로 지점명, 계좌수를 검색하라. (20점)
SELECT branch.branch_name as 지점명, COUNT(account.act_no) as 계좌수
FROM branch 
JOIN account ON branch.branch_uid = account.branch_uid
GROUP BY branch.branch_name 
ORDER BY 계좌수 DESC;


-- 3. 지역별로 계좌수를 검색하라. (개설계좌가 많은 지역순으로) (20점)
SELECT region.region_name as 지역명, COUNT(account.act_no) as 계좌수 
FROM account 
JOIN branch ON branch.branch_uid = account.branch_uid 
JOIN region ON branch.branch_uid = region.region_uid 
GROUP BY region.region_name;


-- 4. 금리가 높은 '예금' 상품의 상품명, 금융사를 검색하라. (금리가 높은 순으로) (20점)
SELECT product.prd_name as 상품명, product.operator as 금융사
FROM product
WHERE product.prd_type_uid = 1
ORDER BY product.interest_rate DESC;


-- 5. ‘대출’ 상품으로 개설된 계좌의 대출잔액 합계를 검색하라.  (20점)
SELECT product.prd_name as 대출_상품, SUM(account.loan_remain_amount) as 대출_잔액
FROM account
JOIN product ON product.prd_uid = account.prd_uid 
WHERE product.prd_type_uid = 2
GROUP BY product.prd_name, account.loan_remain_amount;


-- 6. 보유고객이 제일 적은 지점 5개를 검색하라. (30점)
SELECT * FROM
(
SELECT branch.branch_name as 지점명, COUNT(account.customer_uid) as 보유고객수
FROM branch, account
WHERE account.branch_uid = branch.branch_uid
GROUP BY branch.branch_name
ORDER BY COUNT(account.act_no) ASC
)
WHERE ROWNUM <=5;