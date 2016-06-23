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
  if (!is_null($date_from)) {
    if (!is_null($date_to)) {
      $result = $result->condition('timestamp', array($date_from, $date_to), 'BETWEEN');
    }
    else {
      $result = $result->condition('timestamp', $date_from, '>');
    }
  }
  $result = $result->execute();

  return $result->rowCount();
}

/**
 * Returns array with user-views information for specified node.
 */
function custom_statistics_db_list_users($nid, $date_from = NULL, $date_to = NULL) {
  $result = db_select(CUSTOM_STATISTICS_DB_TABLE_NAME, 'n')
    ->fields('n')
    ->groupBy('uid')
    ->condition('nid', $nid, '=');

  if (!is_null($date_from)) {
    if (!is_null($date_to)) {
      $result = $result->condition('timestamp', array($date_from, $date_to), 'BETWEEN');
    }
    else {
      $result = $result->condition('timestamp', $date_from, '>');
    }
  }
  $result = $result->execute();

  $user_list = [];
  foreach ($result as $item) {
    $user_list[] = array(
      'user' => user_load($item->uid),
      'views' => custom_statistics_db_get_views($nid, $item->uid, $date_from, $date_to),
    );
  }

  return $user_list;
}

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
