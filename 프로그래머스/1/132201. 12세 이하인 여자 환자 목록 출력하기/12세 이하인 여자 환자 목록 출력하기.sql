-- 코드를 입력하세요
SELECT
    -- COALESCE는 앞에서부터 검사해서 NULL 아닌 첫 번째 놈을 가져옴. 
    -- IFNULL은 인자 2개만 가능해서 COALESCE를 쓴다.
    PT_NAME, PT_NO, GEND_CD, AGE, COALESCE(TLNO,'NONE') AS TLNO
FROM PATIENT
WHERE
    AGE <= 12 AND GEND_CD = 'W'
ORDER BY
    AGE DESC, PT_NAME ASC;