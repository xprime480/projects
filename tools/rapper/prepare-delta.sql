--
-- Prepare a delta set between two versions.
--

.mode insert track
.output new_tracks.sql

select *
  from may.track t
 where t.in_library = 1
   and t.rhapsody_id not in 
		 (
 		   select rhapsody_id
 			  from june.track
		 )
   and t.track_id not in
		 (
		   select track_id
			  from june.track
		 )
;

.mode insert ratings
.output new_ratings.sql

select r.*
  from may.ratings r,
  		 may.track t
 where r.ratings_local_track_id = t.track_id
   and t.in_library = 1
   and t.rhapsody_id not in 
		 (
 		   select rhapsody_id
 			  from june.track
		 )
   and t.track_id not in
		 (
		   select track_id
			  from june.track
		 )
;

.output stdout
.mode column
