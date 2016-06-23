<?php
/**
 * @file
 * Contains custom functions.
 */

/**
 * Registers hit of the current node by current user.
 */
function custom_statistics_register_hit($nid, $uid) {
  $today = new DateTime();
  custom_statistics_db_insert_row($nid, $uid, $today->getTimestamp());
}

/**
 * Checks if node type is tracked.
 */
function custom_statistics_is_node_type_tracked($node_type) {
  $tracked_node_types = variable_get('custom_statistics_tracked_node_types');
  foreach ($tracked_node_types as $tracked_type) {
    if ($tracked_type === $node_type) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Checks if user's role is tracked.
 */
function custom_statistics_is_user_role_tracked($user_roles) {
  $tracked_user_roles = variable_get('custom_statistics_tracked_user_roles');
  $is_tracked_user_role = count(array_intersect($tracked_user_roles, $user_roles));
  if ($is_tracked_user_role == 0) {
    return FALSE;
  }
  return TRUE;
}
