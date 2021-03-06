/*
 * Oreka -- A media capture and retrieval platform
 * 
 * Copyright (C) 2005, orecx LLC
 *
 * http://www.orecx.com
 *
 * This program is free software, distributed under the terms of
 * the GNU General Public License.
 * Please refer to http://www.gnu.org/copyleft/gpl.html
 *
 */

package net.sf.oreka.tapestry;

import org.apache.tapestry.BaseComponent;
import org.apache.tapestry.IRequestCycle;
import org.apache.tapestry.annotations.ComponentClass;
import org.apache.tapestry.annotations.Parameter;
import org.apache.tapestry.annotations.Persist;

@ComponentClass
public abstract class MainMenu  extends BaseComponent {
	
	public void myAction(IRequestCycle cycle) {
	
		setHighlight(!getHighlight());
		cycle.activate("Home");
	}	
	
	@Persist
	public abstract boolean getHighlight();
	public abstract void setHighlight(boolean highlight);
	
	@Parameter
	public abstract String getPageName();
	public abstract void setPageName(String name);
	
}
