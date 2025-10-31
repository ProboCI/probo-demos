<?php

/**
 * Implements hook_preprocess_html().
 */
function nel_preprocess_html(&$variables) {
  $node = \Drupal::routeMatch()->getParameter('node');
  if ($node instanceof \Drupal\node\NodeInterface) {
    if ($node->hasField('field_body_css_class')) {
      $css_class = $node->get('field_body_css_class')->value;
      if ($css_class) {
        $variables['attributes']['class'][] = $css_class;
      }
    }
  }
}
