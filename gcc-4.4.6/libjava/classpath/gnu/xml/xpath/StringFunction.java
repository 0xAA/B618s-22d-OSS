/* StringFunction.java -- 
   Copyright (C) 2004 Free Software Foundation, Inc.

This file is part of GNU Classpath.

GNU Classpath is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU Classpath is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Classpath; see the file COPYING.  If not, write to the
Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
02110-1301 USA.

Linking this library statically or dynamically with other modules is
making a combined work based on this library.  Thus, the terms and
conditions of the GNU General Public License cover the whole
combination.

As a special exception, the copyright holders of this library give you
permission to link this library with independent modules to produce an
executable, regardless of the license terms of these independent
modules, and to copy and distribute the resulting executable under
terms of your choice, provided that you also meet, for each linked
independent module, the terms and conditions of the license of that
module.  An independent module is a module which is not derived from
or based on this library.  If you modify this library, you may extend
this exception to your version of the library, but you are not
obligated to do so.  If you do not wish to do so, delete this
exception statement from your version. */

package gnu.xml.xpath;

import java.util.List;
import javax.xml.namespace.QName;
import org.w3c.dom.Node;

/**
 * The <code>string function converts an object to a string as follows:
 * <ul>
 * <li>A node-set is converted to a string by returning the string-value of
 * the node in the node-set that is first in document order. If the node-set
 * is empty, an empty string is returned.</li>
 * <li>A number is converted to a string as follows
 * <ul>
 * <li>NaN is converted to the string NaN</li>
 * <li>positive zero is converted to the string 0</li>
 * <li>negative zero is converted to the string 0</li>
 * <li>positive infinity is converted to the string Infinity</li>
 * <li>negative infinity is converted to the string -Infinity</li>
 * <li>if the number is an integer, the number is represented in decimal
 * form as a Number with no decimal point and no leading zeros, preceded by
 * a minus sign (-) if the number is negative</li>
 * <li>otherwise, the number is represented in decimal form as a Number
 * including a decimal point with at least one digit before the decimal
 * point and at least one digit after the decimal point, preceded by a minus
 * sign (-) if the number is negative; there must be no leading zeros before
 * the decimal point apart possibly from the one required digit immediately
 * before the decimal point; beyond the one required digit after the decimal
 * point there must be as many, but only as many, more digits as are needed
 * to uniquely distinguish the number from all other IEEE 754 numeric
 * values.</li>
 * </ul>
 * </li>
 * <li>The boolean false value is converted to the string false. The boolean
 * true value is converted to the string true.</li>
 * <li>An object of a type other than the four basic types is converted to a
 * string in a way that is dependent on that type.</li>
 * </ul>
 * If the argument is omitted, it defaults to a node-set with the context
 * node as its only member.
 *
 * @author <a href='mailto:dog@gnu.org'>Chris Burdess</a>
 */
final class StringFunction
  extends Expr
{

  final Expr arg;

  StringFunction(List<Expr> args)
  {
    this(args.size() > 0 ? args.get(0) : null);
  }
  
  StringFunction(Expr arg)
  {
    this.arg = arg;
  }

  public Object evaluate(Node context, int pos, int len)
  {
    Object val = (arg == null) ? null : arg.evaluate(context, pos, len);
    return _string(context, val);
  }

  public Expr clone(Object context)
  {
    return new StringFunction((arg == null) ? null :
                              arg.clone(context));
  }

  public boolean references(QName var)
  {
    return (arg == null) ? false : arg.references(var);
  }

  public String toString()
  {
    return (arg == null) ? "string()" : "string(" + arg + ")";
  }
  
}
