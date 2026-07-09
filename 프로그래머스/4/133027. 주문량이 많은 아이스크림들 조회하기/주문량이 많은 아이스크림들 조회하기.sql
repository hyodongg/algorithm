-- 코드를 입력하세요
SELECT
    T.FLAVOR
FROM
    (
        SELECT
            FLAVOR, TOTAL_ORDER
        FROM
            FIRST_HALF
        UNION ALL
        SELECT
            FLAVOR, TOTAL_ORDER
        FROM
            JULY
    ) AS T
GROUP BY
    T.FLAVOR
ORDER BY
    SUM(T.TOTAL_ORDER) DESC
LIMIT 3
            