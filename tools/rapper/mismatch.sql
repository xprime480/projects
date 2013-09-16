--
-- Count instances of same songs with different local track ids.
--
select count(*)
  from june.track a,
       may.track b
 where a.rhapsody_id = b.rhapsody_id
   and a.track_id <> b.track_id
;

--
-- Count instances of track id collisions between different songs.
--
select count(*)
  from june.track a,
       may.track b
 where a.rhapsody_id <> b.rhapsody_id
   and a.track_id = b.track_id
;
