.width 8 8 8

SELECT 
	count(*), in_library, min(ifnull(play_count, 0),1) as played 
FROM 
	track 
GROUP BY 
	in_library, min(ifnull(play_count, 0), 1)
;
