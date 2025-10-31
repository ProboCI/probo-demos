<?php

/**
 * Implements hook_preprocess_paragraph().
 *
 * Apply the "usa-grid" class to all paragraphs.
 */
function nel_preprocess_paragraph(&$variables) {
  $variables['uswds_grid_class'] = 'usa-grid';
}
