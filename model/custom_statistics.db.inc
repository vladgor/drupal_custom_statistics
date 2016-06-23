<?php
/**
 * @file
 * Contains functions with mysql queries.
 */

/**
 * Returns views number for specified nid, uid and date interval.
 */
function custom_statistics_db_get_views($nid, $uid, $date_from = NULL, $date_to = NULL) {
  $result = db_select(CUSTOM_STATISTICS_DB_TABLE_NAME, 'n')
    ->fields('n')
    ->condition('nid', $nid, '=')
    ->condition('uid', $uid, '=');
  if (isset($date_from)) {
    if (isset($date_to)) {
      debug('interval');
      $result = $result->condition('timestamp', array($date_from, $date_to), 'BETWEEN')
        ->execute();
    }
    else {
      debug('single date');
      $result = $result->condition('timestamp', $date_from, '>')
        ->execute();
    }
  }
  else {
    $result->execute();
  }

  return $result->rowCount();
}

/**
 * Increases views number of nid by uid by 1.
 */
/* function custom_statistics_db_register_hit($row) { */
/*   return db_update(CUSTOM_STATISTICS_DB_TABLE_NAME) */
/*     ->fields(array( */
/*       'views' => $row->views + 1, */
/*     )) */
/*     ->condition('nid', $row->nid, '=') */
/*     ->condition('uid', $row->uid, '=') */
/*     ->execute(); */
/* } */

/**
 * Inserts new row with 1 view.
 */
function custom_statistics_db_insert_row($nid, $uid, $date) {
  return db_insert(CUSTOM_STATISTICS_DB_TABLE_NAME)
    ->fields(array(
      'nid' => $nid,
      'uid' => $uid,
      'timestamp' => $date,
    ))
    ->execute();
}

/**
 * Erase table content.
 */
function custom_statistics_db_erase() {
  return db_delete(CUSTOM_STATISTICS_DB_TABLE_NAME)
    ->execute();
}
