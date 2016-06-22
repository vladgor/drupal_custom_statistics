<?php
/**
 * @file
 * Contains custom functions.
 */

/**
 * Creates statistics database table if it doesn't already exits.
 */
function custom_statistics_create_statistics_db_table() {
  if (!db_table_exists(CUSTOM_STATISTICS_DB_TABLE_NAME)) {
    $user_views_schema = array(
      'description' => 'Collects user views for nodes.',
      'fields' => array(
        'nid' => array(
          'type' => 'int',
          'description' => 'The node ID',
          'usigned' => TRUE,
          'not null' => TRUE,
        ),
        'uid' => array(
          'type' => 'int',
          'description' => 'The user ID',
          'usigned' => TRUE,
          'not null' => TRUE,
        ),
        'views' => array(
          'type' => 'int',
          'description' => 'Views number of nid by uid',
          'usigned' => TRUE,
          'not null' => TRUE,
        ),
      ),
      'foreign keys' => array(
        'nid' => array(
          'table' => 'nodes',
          'columns' => array(
            'nid' => 'nid',
          ),
        ),
        'uid' => array(
          'table' => 'users',
          'columns' => array(
            'uid' => 'uid',
          ),
        ),
      ),
    );

    db_create_table(CUSTOM_STATISTICS_DB_TABLE_NAME, $user_views_schema);
  }
}

/**
 * Registers hit of the current node by current user.
 */
function custom_statistics_register_hit($node, &$user) {
  $query = 'SELECT * FROM ' . CUSTOM_STATISTICS_DB_TABLE_NAME . ' ';
  $query .= 'WHERE nid = ' . $node->nid . ' AND uid = ' . $user->uid;
  $result = db_query($query);

  // If query was successful.
  if ($result) {
    // If query returned any results.
    if ($result->rowCount() > 0) {
      // In case of something select only first result from query.
      $selected_user = $result->fetchObject();
      db_update(CUSTOM_STATISTICS_DB_TABLE_NAME)
        ->fields(array(
          'views' => $selected_user->views + 1,
        ))
        ->condition('nid', $node->nid, '=')
        ->condition('uid', $selected_user->uid, '=')
        ->execute();
    }
    else {
      // Insert new row.
      db_insert(CUSTOM_STATISTICS_DB_TABLE_NAME)
        ->fields(array(
          'nid' => $node->nid,
          'uid' => $user->uid,
          'views' => 1,
        ))
        ->execute();
    }
  }
}
