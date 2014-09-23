require 'test_helper'

class CreditCardControllerTest < ActionController::TestCase
  test "should get open" do
    get :open
    assert_response :success
  end

  test "should get debit" do
    get :debit
    assert_response :success
  end

  test "should get credit" do
    get :credit
    assert_response :success
  end

  test "should get close" do
    get :close
    assert_response :success
  end

end
