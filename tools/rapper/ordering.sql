.output ordering.txt

.width 8 25 25

SELECT trim(comments) AS ordering, artist_name, track_name
  FROM track
 WHERE comments IS NOT NULL
   AND length(comments) > 0
   AND in_library = 1
 ORDER BY comments DESC
;

.output stdout
