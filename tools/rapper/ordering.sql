
CREATE TABLE temp_report
AS
SELECT 0 AS rating, 
		 trim(comments) AS ordering, 
		 artist_name, 
		 track_name
  FROM track
 WHERE comments IS NOT NULL
   AND length(comments) > 0
   AND in_library = 1
   AND track_id NOT IN
(
SELECT ratings_local_track_id
  FROM ratings
)
;

INSERT INTO temp_report
SELECT r.ratings_value, 
		 trim(t.comments) AS ordering, 
		 t.artist_name, 
		 t.track_name
  FROM track t,
  		 ratings r       
 WHERE t.comments IS NOT NULL
   AND length(t.comments) > 0
   AND t.in_library = 1
   AND t.track_id = r.ratings_local_track_id
;

.output o2.txt

.width 8 8 25 25

SELECT rating, ordering, artist_name, track_name
  FROM temp_report
 ORDER BY ordering desc
;

DROP TABLE temp_report;

.output stdout
