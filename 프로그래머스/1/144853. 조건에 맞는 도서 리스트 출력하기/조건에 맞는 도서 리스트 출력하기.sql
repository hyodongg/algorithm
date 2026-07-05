-- 코드를 입력하세요
SELECT
    BOOK_ID, 
    DATE_FORMAT(PUBLISHED_DATE, '%Y-%m-%d') AS PUBLISHED_DATE
    -- %Y는 4자리(2021) %y는 2자리(01) %m은 2자리(12) %d는 2자리(01)
FROM
    BOOK
WHERE 
    -- 년도만 빼주는 날짜 전용 함수(YEAR, MONTH, DAY)
    -- WHERE LEFT(PUBLISHED_DATE, 4) = '2021'도 가능
    YEAR(PUBLISHED_DATE) = 2021 
    AND CATEGORY = '인문'
ORDER BY 
    PUBLISHED_DATE;
