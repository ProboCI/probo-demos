<?php

/**
 * Implements hook_preprocess_paragraph__column().
 */
function nel_preprocess_paragraph__uswds_column(&$variables) {
  // Add our own simple CSS hook for columns
  $variables['attributes']['class'][] = 'usda-column';
}
