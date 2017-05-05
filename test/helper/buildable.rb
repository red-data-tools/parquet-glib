# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

module Helper
  module Buildable
    def build_boolean_array(values)
      build_array(Arrow::BooleanArrayBuilder, values)
    end

    private
    def build_array(builder_class, values)
      builder = builder_class.new
      values.each do |value|
        if value.nil?
          builder.append_null
        else
          builder.append(value)
        end
      end
      builder.finish
    end
  end
end
