<?php
// $Id$

/**
 * Field handler to present a link to delete a customer profile.
 */
class commerce_customer_handler_field_customer_profile_link_delete extends commerce_customer_handler_field_customer_profile_link {
  function construct() {
    parent::construct();

    $this->additional_fields['type'] = 'type';
    $this->additional_fields['uid'] = 'uid';
  }

  function render($values) {
    // Ensure the user has access to delete this profile.
    $profile = commerce_customer_profile_new();
    $profile->profile_id = $values->{$this->aliases['profile_id']};
    $profile->type = $values->{$this->aliases['type']};
    $profile->uid = $values->{$this->aliases['uid']};

    if (!commerce_customer_profile_access('update', $profile)) {
      return;
    }

    $text = !empty($this->options['text']) ? $this->options['text'] : t('delete');

    return l($text, 'admin/commerce/customer-profiles/' . $profile->profile_id . '/delete', array('query' => drupal_get_destination()));
  }
}
