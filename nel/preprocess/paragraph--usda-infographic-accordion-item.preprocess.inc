<?php

/**
 * Implements hook_preprocess_paragraph__usda_infographic_accordion_item().
 */
function nel_preprocess_paragraph__usda_infographic_accordion_item(&$variables) {

  // Add the class
  $variables['attributes']['class'][] = 'usa-accordion-item';
  $variables['attributes']['class'][] = 'usda-infographic-accordion-item';

  // Controls
  $controls = 'uswds-paragraph-' . $variables['paragraph']->id();
  $variables['controls'] = $controls;

  // Expand the marked accordion item
  $expanded = (!empty($variables['elements']['#usda_expand']));
  $variables['expanded'] = ($expanded) ? 'true' : 'false';
}
