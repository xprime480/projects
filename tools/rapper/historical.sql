--
-- Select played and rated songs that are not in the library.
--

SELECT
    t.track_id AS 'ID'
FROM
    track t
WHERE
    t.play_count > 1
AND
    t.in_library = 0
AND
    EXISTS
	 (
	     SELECT 
		      1
        FROM
 		      ratings r
		  WHERE
 		      r.ratings_local_track_id = t.track_id
    )
;
