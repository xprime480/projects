
.output playlist_info.txt

select playlist_id,  playlist_name,  rhapsody_playlist_id, last_guid_used
  from playlist
;

select playlist_name, playlist_type, sync_state
  from playlist
;

select playlist_name, mimetypes, hash
  from playlist
;

select *
  from  playlist_track
 order by playlist_id, sequence
;

.output stdout
