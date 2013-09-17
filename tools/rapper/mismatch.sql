--
-- Count instances of same songs with different local track ids.
--
select a.rhapsody_id, a.track_id, b.track_id, a.track_name, b.track_name
  from gold.track a,
       merged.track b
 where a.rhapsody_id = b.rhapsody_id
   and a.track_id <> b.track_id
;

--
-- Count instances of track id collisions between different songs.
--
select count(*)
  from gold.track a,
       merged.track b
 where a.rhapsody_id <> b.rhapsody_id
   and a.track_id = b.track_id
;

--
-- Count instances of rating id collisions between different songs.
--
select b.ratings_id
  from gold.ratings a,
       merged.ratings b
 where a.ratings_local_track_id <> b.ratings_local_track_id
   and a.ratings_id = b.ratings_id
;



