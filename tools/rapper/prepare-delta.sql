--
-- Prepare a delta set between two versions.
--

.mode insert track
.output new_tracks.sql

--
-- Get tracks which are new
--
select *
  from merged.track t
 where t.in_library = 1
   and t.rhapsody_id not in 
		 (
 		   select rhapsody_id
 			  from gold.track
		 )
   and t.track_id not in
		 (
		   select track_id
			  from gold.track
		 )
;

.mode insert ratings
.output new_ratings.sql

--
-- Get any ratings for new tracks.
--
select r.*
  from merged.ratings r,
  		 merged.track t
 where r.ratings_local_track_id = t.track_id
   and t.in_library = 1
   and t.rhapsody_id not in 
		 (
 		   select rhapsody_id
 			  from gold.track
		 )
   and t.track_id not in
		 (
		   select track_id
			  from gold.track
		 )
;

.output stdout
.mode column
