<?php
/**
 * @file
 * Contains functions with mysql queries.
 */

/**
 * Returns filtered rows.
 *
 * @param array $conditions
 *   Associative array with conditions for query.
 *   Array items:
 *     int $nid - id of node that function collects info about,
 *     int $uid - id of user that function collects info about,
 *     DateTime $date_from - date from which function counts views,
 *     DateTime $date_to - date to which function counts views.
 *     string group_by - field that function should group by.
 *     int pager_limit - how many items will be shown when using pager.
 */
function custom_statistics_db_get_rows($conditions) {
  $result = db_select(CUSTOM_STATISTICS_DB_TABLE_NAME, 'n')
    ->fields('n');

  if (!empty($conditions['nid'])) {
    if (is_numeric($conditions['nid'])) {
      $result->condition('nid', $conditions['nid'], '=');
    }
  }
  if (isset($conditions['uid'])) {
    if (is_numeric($conditions['uid'])) {
      $result->condition('uid', $conditions['uid'], '=');
    }
  }
  if (!empty($conditions['date_from'])) {
    $result->condition('timestamp', $conditions['date_from']->getTimestamp(), '>');
  }
  if (!empty($conditions['date_to'])) {
    $result->condition('timestamp', $conditions['date_to']->getTimestamp(), '<');
  }
  if (!empty($conditions['group_by'])) {
    $result->groupBy($conditions['group_by']);
  }
  if (!empty($conditions['pager_limit'])) {
    $result = $result->extend('PagerDefault')
      ->limit($conditions['pager_limit']);
  }
  $result = $result->execute();

  return $result;
}

/**
 * Inserts new row with 1 view.
 *
 * @param int $nid
 *   Id of visited node.
 * @param int $uid
 *   Id of user that visited node.
 * @param DateTime $date
 *   Date when view was registered.
 */
function custom_statistics_db_insert_row($nid, $uid, DateTime $date) {
  return db_insert(CUSTOM_STATISTICS_DB_TABLE_NAME)
    ->fields(array(
      'nid' => $nid,
      'uid' => $uid,
      'timestamp' => $date->getTimestamp(),
    ))
    ->execute();
}

/**
 * Erases table content.
 */
function custom_statistics_db_erase() {
  return db_delete(CUSTOM_STATISTICS_DB_TABLE_NAME)
    ->execute();
}
