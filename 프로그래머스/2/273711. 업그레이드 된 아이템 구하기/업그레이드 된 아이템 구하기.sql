-- 코드를 작성해주세요
SELECT
    ITEM_ID, ITEM_NAME, RARITY
FROM 
    ITEM_INFO
WHERE 
    ITEM_ID IN (
        SELECT ITEM_ID 
        FROM ITEM_TREE 
        WHERE PARENT_ITEM_ID IN (
            SELECT ITEM_ID 
            FROM ITEM_INFO 
            WHERE RARITY = 'RARE'
        ) -- 이 쿼리는 RARE인 것의 ID만 빼내옴
    )
ORDER BY 
    ITEM_ID DESC;