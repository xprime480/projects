.output ordering.txt

.width 5 6 8 25 25

SELECT *
  FROM (
       SELECT coalesce(play_count, 0) as count,
              0 AS rating, 
              trim(comments) AS ordering, 
              artist_name AS artist, 
              track_name AS track
         FROM track
        WHERE comments IS NOT NULL
          AND length(comments) > 0
          AND in_library = 1
          AND track_id NOT IN
              (
              SELECT ratings_local_track_id
                FROM ratings
              )

       UNION

       SELECT coalesce(play_count, 0) as count,
		 		  r.ratings_value AS rating, 
              trim(t.comments) AS ordering, 
              t.artist_name AS artist, 
              t.track_name AS track
         FROM track t,
              ratings r       
        WHERE t.comments IS NOT NULL
          AND length(t.comments) > 0
          AND t.in_library = 1
          AND t.track_id = r.ratings_local_track_id
       )
 ORDER BY ordering desc
;

.output stdout
